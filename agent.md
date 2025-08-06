md_content = """
# (WIP) Codex Agent 자동화 요청 규칙 (2025-08 기준) 

---

## 1. 기본 원칙

- 자동화 작업(빌드, 커밋, 푸시, 머지 등)은 **사용자 추가 확인 없이** 바로 실행함
- Codex Agent가 처리하는 모든 요청은 이 명세서에 따름
- 신규 작업 유형, 예외 사항 등은 이 파일에 계속 추가·갱신

---

## 2. 빌드 서버 요청 분기
사용자가 빌드 요청을 명시적으로 작성한 경우에만 빌드 요청을 수행한다.

### 2-1. 빌드 서버 요청이 필요 없는 경우
- 추가 작업 없이 자동 종료
- build_request.txt 파일 생성하지 않음

### 2-2. 빌드 서버로 요청하는 경우
- build_request.txt 파일을 생성함  
- 아래 템플릿을 따름 (필요 시 세부 내용 추가 가능)

\`\`\`
branch: [작업 브랜치명]
user: [요청자]
action: build
note: [필요시 상세 설명]
\`\`\`

---

## 3. 자동 커밋/푸시/머지 규칙

- 빌드, 테스트, 코드 수정 등 모든 자동화 작업의 결과는  
  **별도 사용자 승인 과정 없이 바로 커밋 및 푸시함**
- Pull Request 병합(merge) 역시, 별도 사용자의 추가 승인 없이 자동 진행  
  (단, 사전 정의된 기준이나 워크플로우 실패 시에는 자동화 중단 및 에러 로그만 전송)
- 커밋 메시지, PR 설명 등은 자동화에서 지정된 포맷 사용  
  (예: \`[Auto] build result for branch XXX\`)

---

## 4. 예외 및 확장 규칙

- 빌드/커밋 외 새로운 액션(post_action 등) 필요 시  
  - agent.md 내 규칙 추가 및 명확한 템플릿 제시
- 추후 “검증 단계” 추가 시에는 해당 내용 별도 섹션으로 명시

---

## 5. 예시 (build_request.txt)

\`\`\`
branch: feat/ai-agent
user: 박일환
action: build
note: 신규 AI Agent 자동화 빌드 요청
\`\`\`

---

> 이 문서는 Codex Agent 자동화의 유일한 공식 명세서임  
> 모든 파이프라인, LLM, 빌드 스크립트는 본 명세를 우선 참조함

## ue compile flow
codex의 작업으로 새 코드가 반영 되었을 경우
- codex_fix.txt 와 codex_fix_fail.txt 파일 제거
- build_request.txt 내용 중 branch_name 값을 작업 branch 이름으로 갱신
- build_request.txt 내용 중 should_build 값(true or false)을 사용자의 명시적 빌드 테스트 요청 유무로 갱신

"""


