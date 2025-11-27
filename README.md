# Zserio C++17 Data/View API Approaches

Comparison of different API designs for separating data storage from schema logic in Zserio C++17.

## Approaches at a Glance

| Approach | View Syntax | Data Syntax | Example |
|----------|-------------|-------------|---------|
| **0 - Current** | `zserio::View<pkg::Compound>` | `pkg::Compound` | [main.cpp](src/approach_0_current/main.cpp) |
| **1 - Namespace** | `pkg::Compound::View` | `pkg::Compound::Data` | [main.cpp](src/approach_1_namespace/main.cpp) |
| **2 - Using** | `pkg::Compound::View` | `pkg::Compound` | [main.cpp](src/approach_2_using/main.cpp) |
| **3 - Top Namespace** | `View::pkg::Compound` | `Data::pkg::Compound` | [main.cpp](src/approach_3_top_namespace/main.cpp) |
| **4 - Top View** | `View::pkg::Compound` | `pkg::Compound` | [main.cpp](src/approach_4_top_view/main.cpp) |
| **5 - Global Data/View** | `nds::view::pkg::Compound` | `nds::data::pkg::Compound` | [main.cpp](src/approach_5_global_data_view/main.cpp) |

## Quick Comparison

- **0**: Current implementation - explicit `zserio::View<T>` wrapper
- **1**: Nested types - `Type::View` and `Type::Data` within same struct
- **2**: Like #1 but data keeps original name, View via using declaration
- **3**: Separate `View::` and `Data::` top-level namespaces
- **4**: Like #3 but data stays in original namespace
- **5**: Global `nds::view::` / `nds::data::` namespaces (NDS-style)

## Details

See [doc/SIG-Zserio 20251128.pdf](doc/SIG-Zserio%2020251128.pdf) for detailed discussion and trade-offs.
