% Noah Morris
% hm1.m

% Code example canvas, slightly changed to fit this purpose
[data,fs]=audioread('Rocky Top.mp3');
data = data(:, 1);
time = 0:1/fs:(length(data)-1)/fs;
figure
plot(time,data)
set(gca,'FontSize', 18);
xlim([0 2.5])
xlabel("Time (sec)");
ylabel("Amplitude");
figure
spectrogram(data,256,250,256,fs,'yaxis');
set(gca,'FontSize', 18);

% low-pass filter for 500hz
filter = lowpass(data, 500, fs);
audiowrite('lpf_500hz.wav', filter, fs);

% low-pass filter for 1Khz
filter = lowpass(data, 1000, fs);
audiowrite('lpf_1khz.wav', filter, fs);

% low-pass filter for 2Khz
filter = lowpass(data, 2000, fs);
audiowrite('lpf_2khz.wav', filter, fs);

% low-pass filter for 10Khz
filter = lowpass(data, 10000, fs);
audiowrite('lpf_10khz.wav', filter, fs);