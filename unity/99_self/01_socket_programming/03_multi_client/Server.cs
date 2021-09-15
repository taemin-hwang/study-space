using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;

public delegate void CallbackTouch(float x, float y);
public delegate void CallbackDirection(int direction);
public delegate void CallbackGaze(float x, float y);
public delegate void CallbackVoice(string message);
public delegate void CallbackHandSkeleton(float Left_x, float Left_y, float Left_z, float Right_x, float Right_y, float Right_z);

public class Receiver
{
    CallbackTouch callbackTouch;
    CallbackDirection callbackDirection;
    CallbackGaze callbackGaze;
    CallbackVoice callbackVoice;
    CallbackHandSkeleton callbackHandSkeleton;
    private TcpClient client;

    public void Run(TcpClient c)
    {
        client = c;
        Thread ReceiveThread = new Thread(new ThreadStart(HandleIncommindRequest));
        ReceiveThread.IsBackground = true;
        ReceiveThread.Start();
    }

    private void HandleIncommindRequest()
    {
        // Get a stream object for reading
        NetworkStream stream = client.GetStream();
        // Read incomming stream into byte array.
        do
        {
            Byte[] bytesTypeOfService = new Byte[4];
            Byte[] bytesDisplayId = new Byte[4];
            Byte[] bytesPayloadLength = new Byte[4];

            int lengthTypeOfService = stream.Read(bytesTypeOfService, 0, 4);
            int lengthDisplayId = stream.Read(bytesDisplayId, 0, 4);
            int lengthPayloadLength = stream.Read(bytesPayloadLength, 0, 4);

            if (lengthTypeOfService <= 0 && lengthDisplayId <= 0 && lengthPayloadLength <= 0)
            {
                break;
            }

            // Reverse byte order, in case of big endian architecture
            if (!BitConverter.IsLittleEndian)
            {
                Array.Reverse(bytesTypeOfService);
                Array.Reverse(bytesDisplayId);
                Array.Reverse(bytesPayloadLength);
            }

            int typeOfService = BitConverter.ToInt32(bytesTypeOfService, 0);
            int displayId = BitConverter.ToInt32(bytesDisplayId, 0);
            int payloadLength = BitConverter.ToInt32(bytesPayloadLength, 0);

            if (typeOfService == 3)
            {
                payloadLength = 1012;
            }

            Byte[] bytes = new Byte[payloadLength];
            int length = stream.Read(bytes, 0, payloadLength);

            ParseIncommingRequest(typeOfService, displayId, payloadLength, bytes);
        } while (true);
    }

    // Handle incomming request
    private void ParseIncommingRequest(int typeOfService, int displayId, int payloadLength, byte[] bytes)
    {
        Debug.Log("=========================================");
        Debug.Log("Type of Service : " + typeOfService);
        Debug.Log("Display Id      : " + displayId);
        Debug.Log("Payload Length  : " + payloadLength);
        switch (typeOfService)
        {
            case 0:
                TouchHandler(displayId, payloadLength, bytes);
                break;
            case 1:
                DirectionHander(displayId, payloadLength, bytes);
                break;
            case 2:
                GazeHandler(displayId, payloadLength, bytes);
                break;
            case 3:
                VoiceHandler(displayId, payloadLength, bytes);
                break;
            case 4:
                BodySkeletonHandler(displayId, payloadLength, bytes);
                break;
            case 5:
                HandSkeletonHandler(displayId, payloadLength, bytes);
                break;
        }
    }

    // Handle Touch Signal
    private void TouchHandler(int displayId, int payloadLength, byte[] bytes)
    {
        Debug.Log("Execute Touch Handler");
        int index = BitConverter.ToInt32(bytes, 0);
        float x_axis = BitConverter.ToSingle(bytes, 4);
        float y_axis = BitConverter.ToSingle(bytes, 8);
        Debug.Log("Index     : " + index);
        Debug.Log("X axis     : " + x_axis);
        Debug.Log("Y axis     : " + y_axis);
        if (callbackTouch != null)
        {
            callbackTouch(x_axis, y_axis);
        }
    }

    // Handle Direction Signal
    private void DirectionHander(int displayId, int payloadLength, byte[] bytes)
    {
        Debug.Log("Execute Direction Handler");
        int direction = BitConverter.ToInt32(bytes, 0);
        Debug.Log("Direction  : " + direction);
        if (callbackDirection != null)
        {
            callbackDirection(direction);
        }

    }

    // Handle Gaze Signal
    private void GazeHandler(int displayId, int payloadLength, byte[] bytes)
    {
        Debug.Log("Execute Gaze Handler");
        int isRight = BitConverter.ToInt32(bytes, 0);
        float x_axis = BitConverter.ToSingle(bytes, 4);
        float y_axis = BitConverter.ToSingle(bytes, 8);
        Debug.Log("isRight  : " + isRight);
        Debug.Log("X axis     : " + x_axis);
        Debug.Log("Y axis     : " + y_axis);
        if (callbackGaze != null)
        {
            callbackGaze(x_axis, y_axis);
        }
    }

    // Handle Voice Signal
    private void VoiceHandler(int displayId, int payloadLength, byte[] bytes)
    {
        Debug.Log("Execute Voice Handler");
        string str = Encoding.Default.GetString(bytes);
        Debug.Log("Text       : " + str);
        if (callbackVoice != null)
        {
            callbackVoice(str);
        }
    }

    // Handle Body Skeleton Signal
    private void BodySkeletonHandler(int displayId, int payloadLength, byte[] bytes)
    {
        Debug.Log("Execute Body Skeleton Handler");
        int numberOfPeople = BitConverter.ToInt32(bytes, 0);
        int Gesture = BitConverter.ToInt32(bytes, 4);
        byte[] tempbytes = new byte[400];
        Array.Copy(tempbytes, 0, bytes, 8, 399);
        string FirstPerson = Encoding.Default.GetString(tempbytes);
        Array.Copy(tempbytes, 0, bytes, 408, 399);
        string SecondPerson = Encoding.Default.GetString(tempbytes);
        Array.Copy(tempbytes, 0, bytes, 808, 399);
        string ThirdPerson = Encoding.Default.GetString(tempbytes);
        Debug.Log("First Person   :   " + FirstPerson);
        Debug.Log("Second Person   :   " + SecondPerson);
        Debug.Log("Third Person   :   " + ThirdPerson);
        // TODO
    }

    // Handle Hand Skeleton Signal
    private void HandSkeletonHandler(int displayId, int payloadLength, byte[] bytes)
    {
        Debug.Log(bytes.Length);
        Debug.Log("Execute Hand Skeleton Handler");
        int sensorPosition = BitConverter.ToInt32(bytes, 0);
        float Left_x = BitConverter.ToSingle(bytes, 4);
        float Left_y = BitConverter.ToSingle(bytes, 8);
        float Left_z = BitConverter.ToSingle(bytes, 12);
        float Right_x = BitConverter.ToSingle(bytes, 16);
        float Right_y = BitConverter.ToSingle(bytes, 20);
        float Right_z = BitConverter.ToSingle(bytes, 24);
        Debug.Log("Left hand     :   (" + Left_x + ", " + Left_y + ", " + Left_z + ")");
        Debug.Log("Right hand     :   (" + Right_x + ", " + Right_y + ", " + Right_z + ")");
        if (callbackHandSkeleton != null)
        {
            callbackHandSkeleton(Left_x, Left_y, Left_z, Right_x, Right_y, Right_z);
        }
    }

    public void SetTouchCallback(CallbackTouch callback)
    {
        callbackTouch = callback;
    }

    public void SetDirectionCallback(CallbackDirection callback)
    {
        callbackDirection = callback;
    }

    public void SetGazeCallback(CallbackGaze callback)
    {
        callbackGaze = callback;
    }

    public void SetVoiceCallback(CallbackVoice callback)
    {
        callbackVoice = callback;
    }

    public void SetHandSkeletonCallback(CallbackHandSkeleton callback)
    {
        callbackHandSkeleton = callback;
    }
}


public class Server : MonoBehaviour
{
    #region private members
    private TcpListener tcpListener;
    private Thread tcpListenerThread;
    private TcpClient connectedTcpClient;
    #endregion

    private static Server instance = null;
    CallbackTouch callbackTouch;
    CallbackDirection callbackDirection;
    CallbackGaze callbackGaze;
    CallbackVoice callbackVoice;
    CallbackHandSkeleton callbackHandSkeleton;

    void Awake()
    {
        Debug.Log("Start Server");
        instance = this;

        // Start TcpServer background thread
        tcpListenerThread = new Thread(new ThreadStart(ListenForIncommingRequest));
        tcpListenerThread.IsBackground = true;
        tcpListenerThread.Start();
    }

    // Update is called once per frame
    void Update()
    {

    }

    public static Server Instance
    {
        get
        {
            if (instance == null)
            {
                return null;
            }
            return instance;
        }
    }

    // Runs in background TcpServerThread; Handles incomming TcpClSient requests
    private void ListenForIncommingRequest()
    {
        try
        {
            // Create listener on 192.168.0.2 port 50001
            tcpListener = new TcpListener(IPAddress.Parse("127.0.0.1"), 50001);
            tcpListener.Start();
            Debug.Log("Server is listening");

            while (true)
            {
                connectedTcpClient = tcpListener.AcceptTcpClient();
                Receiver r = new Receiver();
                r.SetDirectionCallback(callbackDirection);
                r.SetTouchCallback(callbackTouch);
                r.SetGazeCallback(callbackGaze);
                r.SetVoiceCallback(callbackVoice);
                r.SetHandSkeletonCallback(callbackHandSkeleton);
                r.Run(connectedTcpClient);
            }
        }
        catch (SocketException socketException)
        {
            Debug.Log("SocketException " + socketException.ToString());
        }
    }

    public void SetTouchCallback(CallbackTouch callback)
    {
        if (callbackTouch == null)
        {
            callbackTouch = callback;
        }
        else
        {
            callbackTouch += callback;
        }
    }

    public void SetDirectionCallback(CallbackDirection callback)
    {
        if (callbackDirection == null)
        {
            callbackDirection = callback;
        }
        else
        {
            callbackDirection += callback;
        }
    }

    public void SetGazeCallback(CallbackGaze callback)
    {
        if (callbackGaze == null)
        {
            callbackGaze = callback;
        }
        else
        {
            callbackGaze += callback;
        }
    }

    public void SetVoiceCallback(CallbackVoice callback)
    {
        if (callbackVoice == null)
        {
            callbackVoice = callback;
        }
        else
        {
            callbackVoice += callback;
        }
    }

    public void SetHandSkeletonCallback(CallbackHandSkeleton callback)
    {
        if (callbackHandSkeleton == null)
        {
            callbackHandSkeleton = callback;
        }
        else
        {
            callbackHandSkeleton += callback;
        }
    }
}

