# -*- mode: ruby -*-
# vi: set ft=ruby :
Vagrant.configure("2") do |config|

  config.vm.box = "ubuntu/xenial64"
  config.vm.synced_folder ".", "/data"

  config.vm.provision "shell", inline: <<-SHELL

      apt-get update
      apt-get install cmake \
      libcurl4-openssl-dev \
      g++ \
      gcc -y

      export CC=/usr/bin/gcc
      export CXX=/usr/bin/g++

    SHELL

end
