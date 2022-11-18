# squick install script
# author: i0gan
# date: 2022-10-01

who=`whoami`
if [[ $who == "root" ]];then
    sudo=""
else
    sudo="sudo"
fi

bash ./clean.sh

if grep -Eqi "CentOS" /etc/issue || grep -Eq "CentOS" /etc/*-release; then
    DISTRO='CentOS'
elif grep -Eqi "Red Hat Enterprise Linux Server" /etc/issue || grep -Eq "Red Hat Enterprise Linux Server" /etc/*-release; then
    DISTRO='RHEL'
elif grep -Eqi "Aliyun" /etc/issue || grep -Eq "Aliyun" /etc/*-release; then
    DISTRO='Aliyun'
elif grep -Eqi "Fedora" /etc/issue || grep -Eq "Fedora" /etc/*-release; then
    DISTRO='Fedora'
elif grep -Eqi "Debian" /etc/issue || grep -Eq "Debian" /etc/*-release; then
    DISTRO='Debian'
elif grep -Eqi "Ubuntu" /etc/issue || grep -Eq "Ubuntu" /etc/*-release; then
    DISTRO='Ubuntu'
elif grep -Eqi "Raspbian" /etc/issue || grep -Eq "Raspbian" /etc/*-release; then
    DISTRO='Raspbian'
elif grep -Eqi "Arch" /etc/issue || grep -Eq "Arch" /etc/*-release; then
    DISTRO='Arch'
else
    DISTRO='unknow'
fi

if [ $DISTRO == "Debian" ] || [ $DISTRO == "Ubuntu" ] || [ $DISTRO == "Raspbian" ]; then
    $sudo apt-get update
    $sudo apt-get -y install cmake unzip automake make
    $sudo apt-get -y install g++
    $sudo apt-get -y install libtool
    $sudo apt-get -y install libreadline6-dev
    $sudo apt-get -y install libncurses5-dev
    $sudo apt-get -y install pkg-config
	$sudo apt-get -y install libssl-dev
	$sudo apt-get -y install nodejs npm
elif [ $DISTRO == "CentOS" ] || [ $DISTRO == "RHEL" ] || [ $DISTRO == "Fedora" ]  || [ $DISTRO == "Aliyun" ]; then
    $sudo yum -y install cmake unzip automake make
    $sudo yum -y install gcc-c++
    $sudo yum -y install libtool
    $sudo yum -y install readline-devel
    $sudo yum -y install ncurses-devel
    $sudo yum -y install pkg-config
    $sudo yum -y install nodejs npm
else # arch
    $sudo pacman -Sy cmake unzip automake make
    $sudo pacman -S g++
    $sudo pacman -S libtool
    $sudo pacman -S libreadline
    $sudo pacman -S libncurses
    $sudo pacman -S pkg-config
    $sudo pacman -S nodejs npm
fi


# build third_party first
cd ./third_party
bash ./build.sh
cd ..

# build squick
bash ./build.sh

# build admin vue source code
cd ./admin
npm install
bash ./build.sh
cd ..
