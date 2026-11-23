import sys
path = r'H:\Desktop\ArtPlus\CMakeLists.txt'
with open(path, 'r', encoding='utf-8') as f:
    text = f.read()

old = r'''add_test(NAME SaveDocumentTests COMMAND test_save_document)
set_tests_properties(SaveDocumentTests PROPERTIES ENVIRONMENT " PATH=C:/Qt/6.8.3/mingw_64/bin\)'''

new = old + '''

# F-008 Color Management tests
add_executable(test_color_management
 tests/unit/color_management_tests.cpp
)
target_link_libraries(test_color_management PRIVATE ColorManagement Qt6::Core Qt6::Test)
add_test(NAME F-008 COMMAND test_color_management)
set_tests_properties(F-008 PROPERTIES ENVIRONMENT \PATH=C:/Qt/6.8.3/mingw_64/bin\)'''

if old not in text:
 print('old text not found')
 sys.exit(1)

with open(path, 'w', encoding='utf-8') as f:
 f.write(text.replace(old, new))

print('ok')
