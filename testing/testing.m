clc
clear all
close all

[data, fs] = audioread('a.wav');
frameSize = 300;
startPoint = ceil(length(data)/3);
data = data(startPoint:startPoint+frameSize-1);
dlmwrite('data.txt',data);

disp('Testing FFT...');
complexSpec = fft(data,1024);
complexSpec = complexSpec(1:513);
spectrum = abs(complexSpec);

autocor = xcorr(data);
plot(ifft(abs(fft(data,1024)).^2))
figure 
plot(autocor)

cepstrum = ifft(log(abs(fft(data,1024))))

figure
plot(1./abs(fft(lpc(data,12),1024)).^2)