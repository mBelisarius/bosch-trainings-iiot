import json
import requests


def get_content(url, proxies=None, auth=None):
    req = requests.get(url, proxies=proxies, auth=auth)
    if req.status_code == 200:
        return req.content

    raise Exception(f"Request not successful, code {req}")


proxies = {
    "http": "http://<url>:<port>",
    "https": "http://<url>:<port>"
}

proxy_auth = requests.auth.HTTPProxyAuth("<user>", "<password>")

firebase_host = "https://<database-name>.firebaseio.com"
url = firebase_host + "<database-name>.json"

result = get_content(url, proxies, proxy_auth)
print(result)

data = json.loads(result)
print(data)
print(data["subsys_01"]["temperature"]["temp_sensor_00"])
