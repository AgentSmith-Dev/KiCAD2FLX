add_test(
  NAME SmokeConvert
  COMMAND KiCAD2FLX
          ${CMAKE_CURRENT_LIST_DIR}/../CurrentSensor-top.pos
          ${CMAKE_CURRENT_BINARY_DIR}/CurrentSensor-top.flx.pos
          ${CMAKE_CURRENT_LIST_DIR}/../KiCADPackage2FLX.txt
)

add_test(
  NAME CompareAgainstExpected
  COMMAND ${CMAKE_COMMAND} -E compare_files
          ${CMAKE_CURRENT_BINARY_DIR}/CurrentSensor-top.flx.pos
          ${CMAKE_CURRENT_LIST_DIR}/../CurrentSensor-top.flx.pos.expected
)
