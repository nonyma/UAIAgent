import os
import requests
from openai import OpenAI

def codex_fix():
    with open("codex_fix.txt", "r", encoding="utf-8") as f:
        context = f.read()
    prompt = f"""Unreal 프로젝트 빌드 실패 로그입니다. 아래 내용을 분석해, 코드를 고치거나 적절한 조치를 제안해 주세요.\n{context}"""
    client = OpenAI(api_key=os.environ["OPENAI_API_KEY"])
    response = client.chat.completions.create(
        model="gpt-4.1-nano",
        messages=[
            {"role": "system", "content": "You are an expert Unreal Engine C++ developer."},
            {"role": "user", "content": prompt}
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

if __name__ == "__main__":
    if os.path.exists("codex_fix.txt"):
        codex_fix()
    if os.path.exists("build_request.txt"):
        build_request()