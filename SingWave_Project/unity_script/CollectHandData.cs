using System;
using System.IO;
using UnityEngine;
using SenseGloveCs; // SenseGlove SDK가 제공하는 네임스페이스

public class SignLanguageDataCollector : MonoBehaviour
{
    public SenseGlove_Object leftHand;  // 왼손 SenseGlove 장치
    public SenseGlove_Object rightHand; // 오른손 SenseGlove 장치

    private StreamWriter dataWriter;
    private string filePath;

    void Start()
    {
        // 데이터 저장할 파일 설정
        filePath = Application.dataPath + "/SignLanguageData.csv";
        dataWriter = new StreamWriter(filePath, false);
        
        // CSV 파일 헤더 설정
        dataWriter.WriteLine("Timestamp,Hand,Thumb,Index,Middle,Ring,Pinky");

        // 장치가 연결되어 있는지 확인
        if (leftHand == null || rightHand == null)
        {
            Debug.LogError("SenseGlove 장치가 연결되지 않았습니다. 각 장치를 Inspector에서 할당하세요.");
        }
    }

    void Update()
    {
        // 현재 타임스탬프
        string timestamp = DateTime.Now.ToString("HH:mm:ss.fff");

        // 왼손 데이터 수집
        if (leftHand != null && leftHand.IsConnected())
        {
            CollectHandData(leftHand, "Left", timestamp);
        }

        // 오른손 데이터 수집
        if (rightHand != null && rightHand.IsConnected())
        {
            CollectHandData(rightHand, "Right", timestamp);
        }
    }

    private void CollectHandData(SenseGlove_Object hand, string handLabel, string timestamp)
    {
        // 손가락 각도 데이터 가져오기
        float[] fingerAngles = hand.GloveData().GetAllFingerAngles(); 

        // 데이터를 CSV 형식으로 기록
        string dataLine = $"{timestamp},{handLabel}";
        foreach (float angle in fingerAngles)
        {
            dataLine += $",{angle}";
        }

        // 데이터 파일에 쓰기
        dataWriter.WriteLine(dataLine);
        dataWriter.Flush(); // 실시간으로 파일에 기록
    }

    void OnApplicationQuit()
    {
        // 데이터 파일 닫기
        if (dataWriter != null)
        {
            dataWriter.Close();
        }
    }
}
