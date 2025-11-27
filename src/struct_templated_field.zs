package struct_templated_field;

struct Field<T>
{
    T value;
    T arr[3];
    /*function int32 result() {
        return v8 * (value + 1);
    }*/
};

struct Compound
{
    uint32 value;
};

struct StructTemplatedField
{
    Field<uint32>   uint32Field;
    Field<Compound> compoundField;
    Field<string>   stringField;
};
