file(REMOVE_RECURSE
  "../libdeieLogger_static.a"
  "../libdeieLogger_static.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/deieLogger_static.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
