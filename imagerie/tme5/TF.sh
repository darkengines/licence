#!/bin/bash
image=$1
basename=$(basename $image)
ext="${basename##*.}"
name="${basename%.*}"
mkdir $name
cp $image $name
image=$name/$basename
rdf $image $name/"r.inr" $name/"i.inr"
cp $name/"r.inr" $name/"m.inr"
cp $name/"i.inr" $name/"p.inr"
ri $name/"m.inr" $name/"p.inr"
ce $name/"m.inr" $name/"m.inr"
ce $name/"p.inr" $name/"p.inr"
