#!/usr/bin/env bash
./.github/clang-format.sh ./"$@" > ./h_"$@" && mv ./h_"$@" ./"$@"

