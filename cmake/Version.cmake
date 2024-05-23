# cmake-format: off
# Set the project version based on git tags
# This function sets the following variables:
#   - PROJECT_VERSION: The version tag from git, or '0.0.0' if not a git 
#     repository or no version tag is found.
#   - PROJECT_VERSION_SUFFIX: The version suffix which is the commit hash if not
#     a tagged commit, and/or '-custom' if not a GitHub Actions build.
#   - PROJECT_VERSION_FULL: The full version string
# cmake-format: on
function(set_git_tag_as_project_version)
  find_package(Git QUIET)
  if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    # Detect if building in GitHub Actions
    set(BUILD_ENV "local")
    if(DEFINED ENV{GITHUB_ACTIONS})
      set(BUILD_ENV "github")
    endif()

    # Attempt to get version from git describe
    execute_process(
      COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0 --contains --match
              "v*[0-9].*[0-9].*[0-9]"
      WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
      OUTPUT_VARIABLE project_version_tag
      OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)

    # If git describe fails, use the latest version tag and append commit hash.
    if(NOT project_version_tag)
      execute_process(
        COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=0 --match
                "v*[0-9].*[0-9].*[0-9]"
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE project_version_tag
        OUTPUT_STRIP_TRAILING_WHITESPACE)
      execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        OUTPUT_VARIABLE project_commit_hash
        OUTPUT_STRIP_TRAILING_WHITESPACE)
      set(project_commit_hash "+${project_commit_hash}")
    endif()

    if(NOT project_version_tag)
      message(WARNING "No version tag found. Using 'no-version'.")
      set(project_version_tag "no-version")
    endif()

    # Append '-custom' if not a GitHub Actions build
    if(BUILD_ENV STREQUAL "local")
      set(project_version_suffix "${project_commit_hash}-custom")
    endif()

  else()
    message(
      WARNING
        "Git not found or not a git repository. Using 'no-version' and 'no-hash'."
    )
    set(project_version_tag "no-version")
    set(project_version_suffix "no-hash")
  endif()

  # Optionally, strip the 'v' prefix if present
  string(REGEX REPLACE "^v" "" project_version_tag "${project_version_tag}")

  # Make global variables
  set(PROJECT_VERSION_TAG
      "${project_version_tag}"
      CACHE STRING "Project version")
  set(PROJECT_VERSION_SUFFIX
      "${project_version_suffix}"
      CACHE STRING "Project version suffix")
  set(PROJECT_VERSION_FULL
      "${project_version_tag}${project_version_suffix}"
      CACHE STRING "Project full version")

  message(STATUS "Project version tag: ${PROJECT_VERSION_TAG}")
  message(STATUS "Project version suffix: ${PROJECT_VERSION_SUFFIX}")
  message(STATUS "Project full version: ${PROJECT_VERSION_FULL}")
endfunction()
