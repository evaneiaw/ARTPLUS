from pathlib import Path
p = Path('H:/Desktop/ArtPlus/CMakeLists.txt')
text = p.read_text(encoding='utf-8')
block = '''

# F-008 Color Management tests
add_executable(test_color_management tests/unit/color_management_tests.cpp)
target_link_libraries(test_color_management PRIVATE ColorManagement Qt6::Core Qt6::Test)
add_test(NAME F-008 COMMAND test_color_management)
set_tests_properties(F-008 PROPERTIES ENVIRONMENT " PATH=C:/Qt/6.8.3/mingw_64/bin\)
'''
p.write_text(text.rstrip() + block, encoding='utf-8')
print('ok')
