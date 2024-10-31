using System.Collections.Generic;
using UnityEngine;
using SenseGloveCs;

public class SenseGloveInput : MonoBehaviour
{
    private SenseGlove_Device gloveDevice; // SenseGlove 장치 연결을 위한 변수
    public List<float[]> gestureData = new List<float[]>(); // 손가락 데이터 저장 리스트

    void Start()
    {
        // SenseGlove 장치가 있는지 확인하고 초기화
        gloveDevice = SenseGlove_Device.GetSenseGlove();
        if (gloveDevice == null)
        {
            Debug.LogError("SenseGlove 장치를 찾을 수 없습니다.");
        }
    }

    void Update()
    {
        if (gloveDevice != null && gloveDevice.IsConnected())
        {
            // 현재 프레임의 손가락 데이터를 가져옴
            SenseGlove_Data gloveData = gloveDevice.GetGloveData();

            // 손가락 각도와 포지션 데이터를 배열로 저장
            float[] fingerAngles = new float[5];
            for (int i = 0; i < 5; i++)
            {
                fingerAngles[i] = gloveData.GetFingerAngle(i);
            }

            // 데이터 저장 (예: 오토인코더 입력으로 넘기기 위해 사용)
            gestureData.Add(fingerAngles);

            // 필요한 경우 손가락 데이터를 콘솔에 출력 (디버깅 용도)
            Debug.Log("Finger Angles: " + string.Join(", ", fingerAngles));

            // 추가로 회전 데이터나 위치 데이터가 필요하다면 gloveData에서 가져올 수 있음
            Vector3 handPosition = gloveData.handPosition;
            Quaternion handRotation = gloveData.handRotation;

            // handPosition과 handRotation을 이용해 추가 가공 가능
        }
    }

    void OnDisable()
    {
        // 데이터 저장 및 SenseGlove 리소스 해제
        if (gestureData.Count > 0)
        {
            SaveGestureData();
        }

        if (gloveDevice != null)
        {
            gloveDevice.Disconnect();
        }
    }

    private void SaveGestureData()
    {
        // gestureData를 CSV 형식 등으로 저장하여 오토인코더 입력으로 활용
        string path = Application.dataPath + "/GestureData.csv";
        using (System.IO.StreamWriter file = new System.IO.StreamWriter(path))
        {
            foreach (var data in gestureData)
            {
                file.WriteLine(string.Join(",", data));
            }
        }
        Debug.Log("Gesture data saved to " + path);
    }
}
