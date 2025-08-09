# Codex Agent 자동화 요청 규칙 (2025-08 기준)

## 1. 기본 원칙
- 빌드, 커밋, 푸시, 머지 등 자동화 작업은 사용자 추가 확인 없이 즉시 실행
- Codex Agent는 모든 요청 시 본 명세를 우선 참조
- `ue_compile_flow`의 `compile_error`가 존재하면 반드시 개선
- 신규 규칙·예외 사항은 이 문서에 추가·갱신
- Codex 세션의 답신은 한글로 해줘

## 2. build_request.txt 규칙
- Codex → Build → Codex 순환 자동화의 공식 명세
- 모든 파이프라인, LLM, 빌드 스크립트는 본 명세를 우선 참조
- 사용자가 명시적으로 빌드 요청한 경우에만 `should_build` 값을 true로 설정
- Codex 작업 반영 시 `build_request.txt`가 존재하면 다음 항목 갱신:
  - `branch_name` → 작업 브랜치명
  - `should_build` → true/false
  - `user` → codex + codex세션명
  - `compile_error`에서 해결된 내용 제거

## 3. 자동 커밋·푸시·머지 규칙
- 모든 자동화 작업 결과는 즉시 커밋 및 푸시
- Pull Request 병합도 승인 없이 자동 진행  
  (단, 사전 정의된 기준 불충족 또는 워크플로우 실패 시 자동 중단 후 에러 로그 전송)
- 커밋 메시지, PR 설명은 지정 포맷 사용  
  예: `[Auto] build result for branch XXX`

## 4. 예외 및 확장 규칙
- 빌드·커밋 외 새로운 액션이 필요할 경우 agent.md에 규칙과 템플릿 추가
- 검증 단계 추가 시 별도 섹션으로 명시
