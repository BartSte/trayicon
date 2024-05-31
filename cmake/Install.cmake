function(install_with_runtime_dependencies binary)
  # Compatability with the following C libraries across linux distributions is
  # assumed. Use this constant in the install command to exclude these libraries
  # from the installation.
  set(exclude_c_libs_regex
      ".*ld-linux.*\\.so.*" ".*libc\\.so.*" ".*libm\\.so.*" ".*libdbm\\.so.*"
      ".*libpthread\\.so.*")

  install(
    TARGETS ${binary}
    DESTINATION runtime
    RUNTIME_DEPENDENCIES POST_EXCLUDE_REGEXES ${exclude_c_libs_regex})
endfunction()
