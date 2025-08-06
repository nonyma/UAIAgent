import os
import requests
import shutil
import json
from datetime import datetime

def build_request():
    with open("build_request.txt", "r", encoding="utf-8") as f:
        req_data = f.read()
    try:
        req_json = json.loads(req_data)
    except Exception as e:
        print(f"build_request.txt 파싱 오류: {e}")
        return False

    url = os.environ["BUILD_SERVER_URL"]
    resp = requests.post(url, json=req_json)
    print(f"빌드 서버 응답: {resp.status_code} - {resp.text}")

    if 200 <= resp.status_code < 300:
        archive_dir = "build_requests_archive"
        os.makedirs(archive_dir, exist_ok=True)
        now = datetime.now().strftime("%Y%m%d_%H%M%S")
        archive_file = os.path.join(archive_dir, f"build_request_{now}.txt")
        shutil.move("build_request.txt", archive_file)
        print(f"build_request.txt → {archive_file} 이동(아카이브)")
        return True
    else:
        print("빌드 요청 실패: build_request.txt는 남겨둠")
        return False

if __name__ == "__main__":
    if os.path.exists("build_request.txt"):
        build_request()
