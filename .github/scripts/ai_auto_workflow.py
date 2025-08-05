import os
import requests
import shutil
from datetime import datetime
from openai import OpenAI

def codex_fix():
    with open("codex_prompt.txt", "r", encoding="utf-8") as f:
        prompt_template = f.read()
    # 컨텍스트 파일 이름만 명시 (실제 로그/코드는 codex가 직접 파일을 읽어 참고)
    context_file_name = "codex_fix.txt"
    full_prompt = (
        f"{prompt_template}\n"
        f"참고할 컨텍스트 파일 이름: {context_file_name}\n"
    )
    # Codex에게 full_prompt만 전달
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
    # build_request.txt 예: {"project_path": "...", "project_name": "...", "branch_name": "..."}
    import json
    try:
        req_json = json.loads(req_data)
    except Exception as e:
        print(f"build_request.txt 파싱 오류: {e}")
        return
    url = os.environ["BUILD_SERVER_URL"]
    resp = requests.post(url, json=req_json)
    print(f"빌드 서버 응답: {resp.status_code} - {resp.text}")

    # 성공적으로 2xx 응답 받았을 때만 아카이브
    if 200 <= resp.status_code < 300:
        # archive 폴더 준비
        archive_dir = "build_requests_archive"
        os.makedirs(archive_dir, exist_ok=True)

        # 타임스탬프 추가
        now = datetime.now().strftime("%Y%m%d_%H%M%S")
        archive_file = os.path.join(archive_dir, f"build_request_{now}.txt")
        shutil.move("build_request.txt", archive_file)
        print(f"build_request.txt → {archive_file} 이동(아카이브)")
    else:
        print("빌드 요청 실패: build_request.txt는 남겨둠")

if __name__ == "__main__":
    if os.path.exists("codex_fix.txt"):
        codex_fix()
    if os.path.exists("build_request.txt"):
        build_request()