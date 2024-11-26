import pandas as pd

# SenseGlove 데이터 읽기
senseglove_data = pd.read_csv("senseglove_data.csv")

# MediaPipe 데이터 읽기
mediapipe_data = pd.read_csv("hand_landmarks.csv")

# 시간 기준 병합 (내부적으로 가장 가까운 시간 매칭)
combined_data = pd.merge_asof(
    mediapipe_data.sort_values('Time'), 
    senseglove_data.sort_values('Time'), 
    on='Time', 
    direction='nearest'
)

# 병합된 데이터 저장
combined_data.to_csv("combined_data.csv", index=False)
print("병합 완료: combined_data.csv 저장됨")
