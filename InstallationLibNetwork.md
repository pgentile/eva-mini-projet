# Installation de libnetwork #

## Configuration / compilation ##

```
./configure --prefix=$INSTALL_DIR
make install
```

## Chemin des librairies ##

```
export LD_LIBRARY_PATH=$INSTALL_DIR/lib:$LD_LIBRARY_PATH
```