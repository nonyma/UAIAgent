import os
import requests
import json

def is_true(val):
    if val is True or val == 1:
        return True
    if isinstance(val, str) and val.lower() in ("true", "1"):
        return True
    return False

def build_request():
    with open("build_request.txt", "r", encoding="utf-8") as f:
        try:
            req_json = json.load(f)
        except Exception as e:
            print(f"build_request.txt 파싱 오류: {e}")
            return False

    should_build = str(req_json.get("should_build", "")).lower()
    if not is_true(should_build):
        print("should_build 값이 true/1이 아니므로 빌드 요청을 건너뜀")
        return False

    url = os.environ["BUILD_SERVER_URL"]
    resp = requests.post(url, json=req_json)
    print(f"빌드 서버 응답: {resp.status_code} - {resp.text}")

    if 200 <= resp.status_code < 300:
        # req_json["should_build"] = "false"
        # with open("build_request.txt", "w", encoding="utf-8") as f:
        #     json.dump(req_json, f, ensure_ascii=False, indent=2)
        print("빌드 요청 성공: build_request.txt는 정리 되었습니다.")
        return True
    else:
        # req_json["should_build"] = "true"
        # with open("build_request.txt", "w", encoding="utf-8") as f:
        #     json.dump(req_json, f, ensure_ascii=False, indent=2)
        print("빌드 요청 실패: build_request.txt의 error 기록 확인.")
        return False

if __name__ == "__main__":
    if os.path.exists("build_request.txt"):
        build_request()
