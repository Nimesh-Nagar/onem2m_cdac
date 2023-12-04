#!/bin/bash

# check if password is provided or not
source ~/.bashrc
cat ~/.bashrc

# As it is in docker first we need to update
echo $password | sudo -S apt update

# For pipeline setup, check if the Docker has been installed or not
echo $password | sudo -S docker -v > /dev/null 2>&1

# Next we will check if above command successfully executed or not
# Here $? will check previsously executed commnad status
# if 0 means successfully executed and if not then fail
if [ $? == 0 ]
then
  echo "Docker is available"
else
  echo $password | sudo -S apt update && sudo -S apt install ca-certificates curl gnupg && sudo -S install -m 0755 -d /etc/apt/keyrings && curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg && sudo -S chmod a+r /etc/apt/keyrings/docker.gpg
  echo "deb [arch="$(dpkg --print-architecture)" signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu "$(. /etc/os-release && echo "$VERSION_CODENAME")" stable"
  echo $password | sudo -S tee /etc/apt/sources.list.d/docker.list > /dev/null
  echo $password | sudo -S apt update && sudo -S apt install docker-ce docker-ce-cli containerd.io docker-buildx-plugin docker-compose-plugin
  echo "Docker has been installed"
fi

#Execute the command below if you want to create a volume.
echo $password | sudo -S docker volume create gitlab-runner-config > /dev/null 2>&1

#check if the gitlab-runner is running or not
echo $password | sudo -S docker ps | grep gitlab-runner > /dev/null 2>&1

if [ $? == 0 ]
then
  echo "Gitlab runner is running!"
else
  echo $password | sudo -S docker run -d --name gitlab-runner -p 8090:8090 --restart always -v gitlab-runner-config:/etc/gitlab-runner -v /var/run/docker.sock:/var/run/docker.sock gitlab/gitlab-runner
  echo "Gitlab-runner has been installed"
fi


#Register the GitLab Runner installed in Docker.
echo $password | sudo -S docker run --rm -t -v gitlab-runner-config:/etc/gitlab-runner gitlab/gitlab-runner unregister \
  --url "http://gitlab-iot.blr1.cdac.in" \
  --token "ntm5uyFD4ryrU4cU-Rzx"

#Register the GitLab Runner installed in Docker.
echo $password | sudo -S docker run --rm -t -v gitlab-runner-config:/etc/gitlab-runner gitlab/gitlab-runner register \
  --non-interactive \
  --executor "shell" \
  --url "http://gitlab-iot.blr1.cdac.in" \
  --registration-token "ntm5uyFD4ryrU4cU-Rzx" \
  --description "docker-runner" \
  --maintenance-note "Shell script for docker runner" \
  --tag-list "pipeline,stage,test" \
  --run-untagged="true" \
  --locked="false" \
  --access-level="not_protected"








