## Happah Graphics

### Contributing

New developers who wish to contribute to the project can get started by executing the following commands on an Ubuntu 16.04.2 machine, assuming happah-core has already been installed:

```
git clone http://github.com/happah-graphics/happah-graphics.git
cd happah-graphics
./bootstrap
./configure #or ./configure --prefix=...
make
sudo make install
```

Make your changes and run ``` make && sudo make install ``` to update the library.  Finally, run ``` git push origin master ``` to upload your changes to Github.

If you have a release-ready version, tag it by executing ``` git tag -a v0.1 -m "version 0.1" ``` and upload the tag to Github using ``` git push origin v0.1 ``` to push a specific tag or ``` git push origin --tags ``` to push all tags at once.

