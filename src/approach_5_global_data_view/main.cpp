#include <iostream>
#include <assert.h>

#include "nds/view/struct_templated_field/StructTemplatedField.h"
#include "nds/view/struct_templated_field/Field.h"
#include "nds/view/struct_templated_field/Compound.h"

// OR include the Data namespace if one only wants to work with
// Data.
// using namespace nds::data;
// OR alias
// namespace ndsd = nds::data;

// OR alias
// using CompoundView = nds::view::struct_templated_field::Compound;

// possibility to implement overloads for template fields like this was requested in one of the tickets
void print(nds::view::struct_templated_field::Compound field)
{
    std::cout << "Compound";
    std::cout << "{ " << field.value() << " }";
}

template <class T>
void print(T value)
{
    std::cout << value;
}

template <class T>
void print(typename nds::view::struct_templated_field::Field<T> field)
{
    std::cout << "Field<" << typeid(T).name();
    std::cout << "> { .value = ";
    print(field.value());
    std::cout << ", .arr = { ";
    for (const auto& elem : field.arr())
    {
        print(elem);
        std::cout << ", ";
    }
    std::cout << "} }\n";
}

int main()
{
    nds::data::struct_templated_field::StructTemplatedField stf;
    stf.uint32Field.value = 111;
    stf.uint32Field.arr = { 20, 30, 40 };
    stf.stringField.value = "hu";
    stf.stringField.arr = { "do", "re", "mi" };
    stf.compoundField.value.value = 55;
    stf.compoundField.arr = {
        nds::data::struct_templated_field::Compound(100),
        nds::data::struct_templated_field::Compound(200),
        nds::data::struct_templated_field::Compound(300) };

    nds::view::struct_templated_field::StructTemplatedField stfv(stf);
    print(stfv.uint32Field());
    print(stfv.stringField());
    print(stfv.compoundField());

    std::cout << "bitSize=" << zserio::detail::bitSizeOf(stfv, 0) << std::endl;
    std::vector<uint8_t> buf((zserio::detail::bitSizeOf(stfv, 0) + 7) / 8);
    zserio::BitStreamWriter out(buf.data(), 8 * buf.size());
    zserio::detail::write(out, stfv);
    zserio::BitStreamReader in(buf.data(), buf.size());
    nds::data::struct_templated_field::StructTemplatedField stf2;
    zserio::detail::read(in, stf2);
    assert(stf == stf2);
}
