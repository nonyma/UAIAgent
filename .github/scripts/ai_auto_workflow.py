import os
import requests
import shutil
import json
from datetime import datetime
from openai import OpenAI

def codex_fix(build_request_json):
    # build_request_json은 이미 파싱된 dict
    repo = build_request_json.get("repository", "UNKNOWN_REPO")
    branch = build_request_json.get("branch_name", "UNKNOWN_BRANCH")
    project = build_request_json.get("project_name", "UNKNOWN_PROJECT")
    context_info = f"repository: {repo}\nbranch: {branch}\nproject: {project}\n"

    with open("codex_prompt.txt", "r", encoding="utf-8") as f:
        prompt_template = f.read()
    with open("codex_fix.txt", "r", encoding="utf-8") as f:
        error_log = f.read()

    full_prompt = (
        f"{prompt_template}\n"
        f"{context_info}"
        f"\n빌드 에러 로그:\n{error_log}"
    )
    # Codex에 요청
    client = OpenAI(api_key=os.environ["OPENAI_API_KEY"])
    response = client.chat.completions.create(
        model="gpt-4.1-nano",
        messages=[
            {"role": "system", "content": "You are an expert Unreal Engine C++ developer."},
            {"role": "user", "content": full_prompt}
        ]
    )
    with open("codex_suggestion.txt", "w", encoding="utf-8") as f:
        f.write(response.choices[0].message.content)
    print("Codex 개선 요청 완료")

def build_request():
    with open("build_request.txt", "r", encoding="utf-8") as f:
        req_data = f.read()
    try:
        req_json = json.loads(req_data)
    except Exception as e:
        print(f"build_request.txt 파싱 오류: {e}")
        return

    url = os.environ["BUILD_SERVER_URL"]
    resp = requests.post(url, json=req_json)
    print(f"빌드 서버 응답: {resp.status_code} - {resp.text}")

    # 빌드 요청이 성공적으로 끝났다면, 아카이브
    if 200 <= resp.status_code < 300:
        archive_dir = "build_requests_archive"
        os.makedirs(archive_dir, exist_ok=True)
        now = datetime.now().strftime("%Y%m%d_%H%M%S")
        archive_file = os.path.join(archive_dir, f"build_request_{now}.txt")
        shutil.move("build_request.txt", archive_file)
        print(f"build_request.txt → {archive_file} 이동(아카이브)")
    else:
        print("빌드 요청 실패: build_request.txt는 남겨둠")

if __name__ == "__main__":
    if os.path.exists("build_request.txt"):
        # codex_fix() 먼저 실행(필요시)
        with open("build_request.txt", "r", encoding="utf-8") as f:
            build_request_json = json.load(f)
        if os.path.exists("codex_fix.txt"):
            codex_fix(build_request_json)
        build_request()  # 마지막에 요청/아카이브
