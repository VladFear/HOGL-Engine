#!/bin/bash

OUT_TEST_DIR="out/tests"


if [ -d "${OUT_TEST_DIR}" ]; then
	for i in `find ${OUT_TEST_DIR} -type f` ; do
		./$i;
		sleep 1
	done
else
	echo "Error: Directory with tests (${OUT_TEST_DIR}) does not exist."
fi
