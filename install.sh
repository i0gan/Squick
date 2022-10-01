# squick install script

bash ./clean.sh

if grep -Eqi "CentOS" /etc/issue || grep -Eq "CentOS" /etc/*-release; then
    DISTRO='CentOS'
    PM='yum'
elif grep -Eqi "Red Hat Enterprise Linux Server" /etc/issue || grep -Eq "Red Hat Enterprise Linux Server" /etc/*-release; then
    DISTRO='RHEL'
    PM='yum'
elif grep -Eqi "Aliyun" /etc/issue || grep -Eq "Aliyun" /etc/*-release; then
    DISTRO='Aliyun'
    PM='yum'
elif grep -Eqi "Fedora" /etc/issue || grep -Eq "Fedora" /etc/*-release; then
    DISTRO='Fedora'
    PM='yum'
elif grep -Eqi "Debian" /etc/issue || grep -Eq "Debian" /etc/*-release; then
    DISTRO='Debian'
    PM='apt-get'
elif grep -Eqi "Ubuntu" /etc/issue || grep -Eq "Ubuntu" /etc/*-release; then
    DISTRO='Ubuntu'
    PM='apt-get'
elif grep -Eqi "Raspbian" /etc/issue || grep -Eq "Raspbian" /etc/*-release; then
    DISTRO='Raspbian'
    PM='apt-get'
elif grep -Eqi "Arch" /etc/issue || grep -Eq "Arch" /etc/*-release; then
    DISTRO='Arch'
    PM='pacman'
else
    DISTRO='unknow'
fi

if [ $DISTRO == "Debian" ] || [ $DISTRO == "Ubuntu" ] || [ $DISTRO == "Raspbian" ]; then
    sudo apt-get -y install cmake unzip automake
    sudo apt-get -y install g++-7
    sudo apt-get -y install libtool
    sudo apt-get -y install libstdc++-static
    sudo apt-get -y install libreadline6-dev
    sudo apt-get -y install libncurses5-dev
    sudo apt-get -y install pkg-config
	sudo apt-get -y install libssl-dev
elif [ $DISTRO == "CentOS" ] || [ $DISTRO == "RHEL" ] || [ $DISTRO == "Fedora" ]  || [ $DISTRO == "Aliyun" ]; then
    sudo yum -y install centos-release-scl
	sudo yum -y install devtoolset-7
	sudo scl enable devtoolset-7 bash
    sudo yum -y install libtool
    sudo yum -y install readline-devel
    sudo yum -y install ncurses-devel
    sudo yum -y install libstdc++-static
    sudo yum -y install pkg-config
else # arch
    sudo pacman -Sy cmake unzip automake
    sudo pacman -S g++
    sudo pacman -S libtool
    sudo pacman -S libreadline
    sudo pacman -S libncurses
    sudo pacman -S pkg-config
fi

# build third_party first
cd ./third_party
bash ./build.sh

# build squick
cd ../
bash ./build.sh