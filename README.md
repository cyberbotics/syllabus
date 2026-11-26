# Syllabus

## Test URL

All the simulations and animations can be tested online from this index page:

https://cyberbotics.github.io/syllabus/index.html

## Simulation Server

The simulations are run by a [webots-server](https://github.com/cyberbotics/webots-server) simulation server started with `python3 simulation_server.py config/simulation/syllabus.json`, where `config/simulation/syllabus.json` contains:

```json
{
  "server": "simulation.webots.cloud",
  "port": 3000,
  "portRewrite": true,
  "ssl": true,
  "webotsHome": "/home/cyberbotics/webots",
  "allowedRepositories": [
    "https://github.com/cyberbotics/syllabus/"
  ],
  "notify": [],
  "logDir": "log/",
  "monitorLogEnabled": true,
  "docker": true,
  "persistantDockerImages": [
    "cyberbotics/webots.cloud:R2025a-ubuntu22.04",
    "benjamindeleze/theia-test:test3"
  ]
}
```
