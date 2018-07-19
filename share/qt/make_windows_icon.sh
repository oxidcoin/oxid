#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/oxid.ico

convert ../../src/qt/res/icons/oxid-16.png ../../src/qt/res/icons/oxid-80.png ../../src/qt/res/icons/oxid-80.png ${ICON_DST}
