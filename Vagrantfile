# -*- mode: ruby -*-
# vi: set ft=ruby :
Vagrant.configure("2") do |config|

  config.vm.box = "hashicorp/precise64"
  config.vm.synced_folder ".", "/data"

  config.vm.provision "shell", inline: <<-SHELL
      apt-get update
      apt-get install cmake \
      python-software-properties \
      software-properties-common \
      libcurl4-opensll-dev \
      build-essential -y

      add-apt-repository ppa:ubuntu-toolchain-r/test
      apt-get update
      apt-get install gcc-5 g++-5 -y

      ln -f -s /usr/bin/g++-5 /usr/bin/g++
      ln -f -s /usr/bin/gcc-5 /usr/bin/gcc
    SHELL

end
