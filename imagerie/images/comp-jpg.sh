#! /bin/bash

function passebas {
### parametres ###
    x=$1
    y=$2
    r=$3
    o=$4
    # coordonnees du cercle
    x1=$((x/2-r/2))
    y1=$((y/2-r/2))
    # on dessine un cercle
    cat > c.xv <<EOF
##!draw(a $x1 $y1 $r)
##!dump(c.inr)
##!EXIT
EOF
    xvis -fnull $x $y -xsh c.xv
    extg c.inr -v 1 | anac - c.chn -fc
    # on remplit le cercle
    fillc c.chn $o -x $x -y $y -pos
    rm -f c.chn c.inr c.xv
}


rdf cameraman.inr.gz r i
ri r i



dims=($(par -x -y $img ))
x=${dims[1]}
y=${dims[3]}

passebas $x $y  100 bas.inr
logic -inv bas.inr >haut.inr

rm -f bas.inr

mu r bas.inr > rs

