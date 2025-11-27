#include <iostream>
#include <assert.h>

#include "struct_templated_field/StructTemplatedField.h"
#include "struct_templated_field/Field.h"
#include "struct_templated_field/Compound.h"

using namespace struct_templated_field;

// possibility to implement overloads for template fields like this was requested in one of the tickets
// void print(zserio::View<Compound> field) OR
void print(typename Compound::View field)
{
    std::cout << "Compound";
    std::cout << "{ " << field.value() << " }";
}

template <class T>
void print(const T& value)
{
    std::cout << value;
}

template <class T>
// void print(zserio::View<Field<T>> field) OR
void print(typename Field<T>::View field) // requires print<T>() call
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
    static_assert(std::is_same_v<Field<int>, typename Field<int>::Data>);
    static_assert(std::is_same_v<zserio::View<Field<int>>, typename Field<int>::View>);

    StructTemplatedField stf;
    // OR StructTemplatedField::Data stf;
    stf.uint32Field.value = 111;
    stf.uint32Field.arr = { 20, 30, 40 };
    stf.stringField.value = "hu";
    stf.stringField.arr = { "do", "re", "mi" };
    stf.compoundField.value.value = 55;
    stf.compoundField.arr = { Compound(100), Compound(200), Compound(300) };

    StructTemplatedField::View stfv(stf);
    // OR zserio::View<StructTemplatedField> stfv(stf)
    print<zserio::UInt32>(stfv.uint32Field());
    print<zserio::String>(stfv.stringField());
    print<Compound::Data>(stfv.compoundField());

    std::cout << "bitSize=" << zserio::detail::bitSizeOf(stfv, 0) << std::endl;
    std::vector<uint8_t> buf((zserio::detail::bitSizeOf(stfv, 0) + 7) / 8);
    zserio::BitStreamWriter out(buf.data(), 8 * buf.size());
    zserio::detail::write(out, stfv);
    zserio::BitStreamReader in(buf.data(), buf.size());
    StructTemplatedField stf2;
    zserio::detail::read(in, stf2);
    assert(stf == stf2);
}
