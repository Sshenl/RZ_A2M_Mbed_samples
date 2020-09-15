clear;close all;

% 指令
[instruction, FS] = audioread('english.m4a');

% 语音助手唤醒口令
[key, FS] = audioread('yoyo.m4a');
%key = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0;0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]';
%key = key(floor(size(key,1)*2/7):floor(size(key,1)*6/7), :);


% 归一化
 key(:,1) = key(:,1)/max(key(:,1));
 key(:,2) = key(:,2)/max(key(:,2));
instruction(:,1) = instruction(:,1)/max(instruction(:,1));
instruction(:,2) = instruction(:,2)/max(instruction(:,2));

key = [key; instruction];


% 原始音频波形
figure; plot(instruction) 
title('original audio');

% 升采样
fs = 96000;
instruction = resample(instruction,fs, FS);
key = resample(key,fs, FS);

% 低通滤波
lowpass = lowpass_5khz;
instruction = filter(lowpass, instruction);
instruction(:,1) = instruction(:,1)/max(instruction(:,1));
instruction(:,2) = instruction(:,2)/max(instruction(:,2));
lowpass = lowpass_8khz;
key = filter(lowpass, key);
key(:,1) = key(:,1)/max(key(:,1));
key(:,2) = key(:,2)/max(key(:,2));

% 指令的攻击信号生成（不可破解声纹）
sig_mod1 = instruction + 1;

% 语音助手唤醒口令的攻击信号生成（可破解声纹）
sig_mod2 = key + 1;
k = 0.75;
test1 = (-k+sqrt(k*k+4*sig_mod2))/2;
test1(:,1) = test1(:,1)/max(test1(:,1));
test1(:,2) = test1(:,2)/max(test1(:,2));

% 调制频率
fc = 28000;
highpass = highpass_21khz;

% 指令调制
ultrasond1 = modulate(sig_mod1,fc,fs,'am');
ultrasond1 = filter(highpass, ultrasond1);

% 语音助手唤醒口令调制
ultra_test1 = modulate(test1,fc,fs,'am');
ultra_test1 = filter(highpass, ultra_test1);
ultra_test1(:,1) = ultra_test1(:,1)/max(ultra_test1(:,1));
ultra_test1(:,2) = ultra_test1(:,2)/max(ultra_test1(:,2));

ultrasond1 = real(ultrasond1);
ultrasond1 = ultrasond1./max(ultrasond1);
ultra_test1 = ultra_test1/max(ultra_test1);

for i = 1:100
    sound(ultra_test1,fs);
    pause(1.75);

%     sound(ultrasond1 ,fs);
   pause
end
