cmake_minimum_required(VERSION 3.22)
project(ArtPlus VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Test ZlibPrivate)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Source files

set(DOCUMENT_SOURCES
    src/document/document_model.cpp
    src/document/document_model.h
    src/document/document_serializer.cpp
    src/document/document_serializer.h
    src/document/undo.cpp
    src/document/undo.h
    src/document/document_save_manager.cpp
    src/document/document_save_manager.h
)

set(PDF_SOURCES
    src/pdf/pdf_types.cpp
    src/pdf/pdf_types.h
    src/pdf/pdf_lexer.cpp
    src/pdf/pdf_lexer.h
    src/pdf/pdf_parser.h
    src/pdf/pdf_document.cpp
    src/pdf/pdf_document.h
    src/pdf/pdf_content.cpp
    src/pdf/pdf_content.h
    src/pdf/pdf_importer.cpp
    src/pdf/pdf_importer.h
    src/pdf/pdf_exporter.cpp
    src/pdf/pdf_exporter.h
)

set(UI_SOURCES
    src/ui/main_window.cpp
    src/ui/main_window.h
)

set(PREPRESS_SOURCES
    src/prepress/bearer_bar.cpp
    src/prepress/bearer_bar.h
    src/prepress/cut_mark.cpp
    src/prepress/cut_mark.h
    src/prepress/markset_processor.cpp
    src/prepress/markset_processor.h
    src/prepress/trapping.cpp
    src/prepress/trapping.h
    src/prepress/step_repeat.cpp
    src/prepress/step_repeat.h
    src/prepress/packaging.cpp
    src/prepress/packaging.h
    src/prepress/marks.cpp
    src/prepress/marks.h
    src/prepress/imposition.cpp
    src/prepress/imposition.h
    src/prepress/color_manipulation/color_manipulation_layer.cpp
    src/prepress/color_manipulation/color_manipulation_layer.h
)

set(AUTOMATION_SOURCES
    src/automation/action_list.cpp
    src/automation/action_list.h
    src/automation/scripting.cpp
    src/automation/scripting.h
    src/automation/recovery.cpp
    src/automation/recovery.h
    src/automation/performance.cpp
    src/automation/performance.h
)

# Common include directory for all targets using project sources
function(setup_target_incdirs target)
    target_include_directories(${target} PRIVATE ${CMAKE_SOURCE_DIR}/src)
endfunction()

# Integration probes
add_executable(form_parser_probe
    tests/integration/form_parser_probe.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(form_parser_probe PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::ZlibPrivate)
setup_target_incdirs(form_parser_probe)

add_executable(smask_probe
    tests/integration/smask_probe.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(smask_probe PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::ZlibPrivate)
setup_target_incdirs(smask_probe)

add_executable(mirror_probe
    tests/integration/mirror_probe.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(mirror_probe PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::ZlibPrivate)
setup_target_incdirs(mirror_probe)

add_executable(page_placeholders
    tests/integration/page_placeholders.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(page_placeholders PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::ZlibPrivate)
setup_target_incdirs(page_placeholders)

add_executable(form_transform_probe
    tests/integration/form_transform_probe.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(form_transform_probe PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::ZlibPrivate)
setup_target_incdirs(form_transform_probe)

add_executable(pdf_smoke
    tests/integration/pdf_smoke.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(pdf_smoke PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::ZlibPrivate)
setup_target_incdirs(pdf_smoke)

add_executable(form_xobject_test
    tests/integration/form_xobject_test.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(form_xobject_test PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
setup_target_incdirs(form_xobject_test)
add_test(NAME FormXObjects COMMAND form_xobject_test)
set_tests_properties(FormXObjects PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")
add_test(NAME PdfSmoke COMMAND pdf_smoke)
set_tests_properties(PdfSmoke PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")

# Main application
add_executable(ArtPlus
    src/app/main.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
    ${UI_SOURCES}
    ${AUTOMATION_SOURCES}
)
target_link_libraries(ArtPlus PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::ZlibPrivate)
setup_target_incdirs(ArtPlus)

enable_testing()

# Unit tests
add_executable(unit_tests
    tests/unit/test_main.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
    ${AUTOMATION_SOURCES}
)
target_link_libraries(unit_tests PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
setup_target_incdirs(unit_tests)
add_test(NAME UnitTests COMMAND unit_tests)
set_tests_properties(UnitTests PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")

add_executable(pdf_roundtrip_test
    tests/unit/test_pdf_roundtrip.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(pdf_roundtrip_test PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
setup_target_incdirs(pdf_roundtrip_test)
add_test(NAME PdfRoundTrip COMMAND pdf_roundtrip_test)
set_tests_properties(PdfRoundTrip PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")

add_executable(editing_test
    tests/unit/test_editing.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(editing_test PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
setup_target_incdirs(editing_test)
add_test(NAME EditingTests COMMAND editing_test)
set_tests_properties(EditingTests PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")

add_executable(integration_test_basic
    tests/integration/test_integration_basic.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(integration_test_basic PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
setup_target_incdirs(integration_test_basic)
add_test(NAME IntegrationTestBasic COMMAND integration_test_basic)
set_tests_properties(IntegrationTestBasic PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")

add_executable(test_markset_processor
    tests/unit/test_markset_processor.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_include_directories(test_markset_processor PRIVATE ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(test_markset_processor PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
add_test(NAME MarkSetProcessor COMMAND test_markset_processor)
set_tests_properties(MarkSetProcessor PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")

add_executable(bearer_bar_test
    tests/unit/test_bearer_bar.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(bearer_bar_test PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
setup_target_incdirs(bearer_bar_test)
add_test(NAME BearerBarTests COMMAND bearer_bar_test)
set_tests_properties(BearerBarTests PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")

add_executable(test_cut_mark
    tests/unit/test_cut_mark.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(test_cut_mark PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
setup_target_incdirs(test_cut_mark)
add_test(NAME CutMarkTests COMMAND test_cut_mark)
set_tests_properties(CutMarkTests PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")

add_executable(test_save_document
    tests/unit/test_save_document.cpp
    ${DOCUMENT_SOURCES}
    ${PDF_SOURCES}
    ${PREPRESS_SOURCES}
)
target_link_libraries(test_save_document PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets Qt6::Test Qt6::ZlibPrivate)
setup_target_incdirs(test_save_document)
add_test(NAME SaveDocumentTests COMMAND test_save_document)
set_tests_properties(SaveDocumentTests PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")

# Include color_management module (F-008)
add_subdirectory(src/color_management)
# F-008 Color Management tests
add_executable(test_color_management tests/unit/color_management_tests.cpp)
target_link_libraries(test_color_management PRIVATE ColorManagement Qt6::Core Qt6::Test)
add_test(NAME F-008 COMMAND test_color_management)
set_tests_properties(F-008 PROPERTIES ENVIRONMENT "PATH=C:/Qt/6.8.3/mingw_64/bin")