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

url = "https://random.dog/woof.json"

content = get_content(url, proxies, proxy_auth)
img_url = json.loads(content)["url"]
img = get_content(img_url, proxies)

with open("result.jpg", "wb") as f:
    f.write(img)
