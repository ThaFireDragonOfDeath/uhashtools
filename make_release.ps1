# This file is part of µHashtools.
# µHashtools is a small graphical file hashing tool for Microsoft Windows.
# 
# SPDX-FileCopyrightText: 2024 Marcel Gosmann <thafiredragonofdeath@gmail.com>
# SPDX-License-Identifier: CC0-1.0

# This script automates the process of creating a release
# archive of µHashtools.

# Set script execution options
$ErrorActionPreference = "Stop"

# Constants from makefile
$product_ascii_name = "uhashtools"
$product_version = "0.3.0"
$distout_dir_name = "dist_out"

# Directory names from makefile
$dist_target_name = "${product_ascii_name}_v${product_version}"

# Directory paths from makefile
$distout_dir_path = ".\${distout_dir_name}\${dist_target_name}"
$distout_src_pkg_dir_path = "${distout_dir_path}\source_code"

# Constants
$make_release_out_dir_name = "make_release_out"
$make_release_cache_dir_name = "cache"

# Directory names
$project_src_dir_name = "${product_ascii_name}_v${product_version}_src"
$release_archive_dir_name = "${dist_target_name}_bin_x64"

# Directory paths
$make_release_out_dir_path = ".\${make_release_out_dir_name}"
$make_release_cache_dir_path = "${make_release_out_dir_path}\${make_release_cache_dir_name}"
$project_src_dir_path = "${make_release_cache_dir_path}\${project_src_dir_name}"
$release_archive_dir_path = "${make_release_cache_dir_path}\${release_archive_dir_name}"

# File names
$project_src_zip_name = "${project_src_dir_name}.zip"
$release_archive_zip_name = "${release_archive_dir_name}.zip"

# File paths
$project_src_zip_path = "${make_release_cache_dir_path}\${project_src_zip_name}"
$release_archive_zip_path = "${make_release_out_dir_path}\${release_archive_zip_name}"

# Ensure we're in a clean state
"Cleaning up the source folder by calling 'nmake clean'."
nmake clean

# Create the output directory structure.
"Creating output directory structure at '${make_release_out_dir_path}'"
New-Item -ItemType "directory" -Path ".\" -Name $make_release_out_dir_name
New-Item -ItemType "directory" -Path $make_release_out_dir_path -Name $make_release_cache_dir_name
New-Item -ItemType "directory" -Path $make_release_cache_dir_path -Name $project_src_dir_name
New-Item -ItemType "directory" -Path $make_release_cache_dir_path -Name $release_archive_dir_name

# Copy all sources into a directory and them make a source archive from that.
"Creating source archive at '${project_src_zip_path}'."
Copy-Item -Path ".\*" -Recurse -Exclude $make_release_out_dir_name -Destination $project_src_dir_path
Compress-Archive -Path $project_src_dir_path -DestinationPath $project_src_zip_path

# Building µHashtools in release mode and create the binary distribution.
"Starting the build process by running 'nmake BUILD_MODE=Release dist'."
nmake BUILD_MODE=Release dist

# Copy the source archive into the correct folder with the binary distribution
# to finish the release in the dist_out folder.
"Copying source archive into '${distout_src_pkg_dir_path}'"
Copy-Item -Path $project_src_zip_path -Destination $distout_src_pkg_dir_path

# Now copy the whole distout file tree into the cache within the directory
# with the correct final name of the release and compress this directory into
# the final release archive file.
"Creating release archive."
Copy-Item -Path "${distout_dir_path}\*" -Recurse -Destination $release_archive_dir_path
Compress-Archive -Path $release_archive_dir_path -DestinationPath $release_archive_zip_path
"Successfully created release archive at '${release_archive_zip_path}'."