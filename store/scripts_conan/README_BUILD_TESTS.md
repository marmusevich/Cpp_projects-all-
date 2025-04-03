clone project from repo
```Console
git clone https://luxproject.luxoft.com/stash/scm/foxcoa/connection-manager.git
```
# AOSP
Do make module, 
go to **SYSTEM_BUILD_DIR**
```Console
cd  SYSTEM_BUILD_DIR
source build/envsetup.sh
lunch 49
```
make **FoxconnConnectionManager**
```Console
m FoxconnConnectionManager
```
or build all in folder path
```Console
mm vendor/connection-manager
```

# For unix like system
### Disable Zscaler! 

```Console
sudo update-alternatives --install /usr/bin/python python /usr/bin/python3 1
sudo apt install python3-pip -y
pip install conan
source ~/.profile

conan profile detect
```


The gtest may require:
```Console
sudo apt-get install pkg-config
```

Run script to build
```Console
./scripts/lin_build.sh
```


# Coverage
Prerequisite install `lcov`, repeat steps described in **For unix like system** part

```Console
sudo apt install lcov
```

Run script
```Console
./scripts/lin_coverage.sh
```
**NOTE to the best result:**
- enable disabled test (marked `DISABLED_`) - disabled due to big time of the test
- enable loggig, set `ENABLE_LOGING_IN_TEST` to 1 in */manager/test/CMakeLists.txt*

# For windows system
### Disable Zscaler! 

manually setup the Python and pyp
install conan
```Console
pip install conan

conan profile detect
```

run to create solution file
```Console
/scripts/win_build.bat
```



