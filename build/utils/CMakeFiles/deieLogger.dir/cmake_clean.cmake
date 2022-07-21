file(REMOVE_RECURSE
  "../libdeieLogger.pdb"
  "../libdeieLogger.so"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/deieLogger.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
