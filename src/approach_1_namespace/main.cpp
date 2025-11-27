#include <iostream>
#include <assert.h>

#include "struct_templated_field/StructTemplatedField.h"
#include "struct_templated_field/Field.h"
#include "struct_templated_field/Compound.h"

using namespace struct_templated_field;

// possibility to implement overloads for template fields like this was requested in one of the tickets
void print(Compound::View field)
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
void print(typename Field::View<T> field)
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
    StructTemplatedField::Data stf;
    stf.uint32Field.value = 111;
    stf.uint32Field.arr = { 20, 30, 40 };
    stf.stringField.value = "hu";
    stf.stringField.arr = { "do", "re", "mi" };
    stf.compoundField.value.value = 55;
    stf.compoundField.arr = { Compound::Data(100), Compound::Data(200), Compound::Data(300) };

    static_assert(std::is_same_v<StructTemplatedField::View, zserio::View<StructTemplatedField::Data>>);
    StructTemplatedField::View stfv(stf);
    print(stfv.uint32Field());
    print(stfv.stringField());
    print(stfv.compoundField());

    std::cout << "bitSize=" << zserio::detail::bitSizeOf(stfv, 0) << std::endl;
    std::vector<uint8_t> buf((zserio::detail::bitSizeOf(stfv, 0) + 7) / 8);
    zserio::BitStreamWriter out(buf.data(), 8 * buf.size());
    zserio::detail::write(out, stfv);
    zserio::BitStreamReader in(buf.data(), buf.size());
    StructTemplatedField::Data stf2;
    zserio::detail::read(in, stf2);
    assert(stf == stf2);
}
