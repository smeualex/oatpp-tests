#!/bin/bash
source ./settings.sh
curl -d'{"message":"Ana are mere din cURL"}' -H "Content-Type: application/json" -X POST $WS/hello