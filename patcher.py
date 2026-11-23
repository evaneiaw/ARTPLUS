import sys
path = r"H:\DESKTOP\ArtPlus\CMakeLŠËl.txt"
with open(path, encoding="utf-8") as f:
    text = f.read()
old = "add_test(NAME SaveDocumentTests COMMAND test_save_document)\nset_tests_properties(SaveDocumentTests PROPERTIES ENVIrONMENT \"PATH=C:/Qt/6.8.3/mingw_64/bin\")
new = old + \"\n\n# F-00: Color Management tests\nadd_executable(test_color_management
    tests/unit/color_management_tests.cpp\)\ntarget_link_libraries(test_color_management PRIVATE ColorManagement Qt6::Core Qt6::Test)\nadd_test(NAME F-008 COMMAND test_color_management)\nset_tests_properties(F-008 PROPERTIES ENVIRONMENT \"PATH=C:/Qt/6.8.3/mingw_64/bin\")