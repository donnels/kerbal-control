#!/usr/bin/env bash
#Author: Sean Donnellan
#call plantul java to make plantumls

outDir="/data"
appDir="/opt/app"
callPlantuml="java -jar ${appDir}/plantuml-1.2022.0.jar"


#go to data volume
cd $outDir

#if this is a test run copy the test files across
if [ $1 = "/opt/app/reference.plantuml" ]; then
    cp ${appDir}/reference.asciidoc $outDir
    cp ${appDir}/reference.plantuml $outDir
fi

#make the SVGs
$callPlantuml -o $outDir -tsvg $@ 
#make the PNGs (actually default but added the -tpng anyway)
$callPlantuml -o $outDir -tpng $@ 