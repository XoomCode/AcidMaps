add_library (acid-maps SHARED acid_maps.cc)
set_target_properties(example PROPERTIES 
  LIBRARY_OUTPUT_DIRECTORY "../bin"
)
