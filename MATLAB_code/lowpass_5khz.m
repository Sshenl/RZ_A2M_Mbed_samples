function Hd = lowpass_5khz
%LOWPASS_5KHZ Returns a discrete-time filter object.

% MATLAB Code
% Generated by MATLAB(R) 9.1 and the Signal Processing Toolbox 7.3.
% Generated on: 17-Mar-2020 16:28:51

% Equiripple Lowpass filter designed using the FIRPM function.

% All frequency values are in Hz.
Fs = 96000;  % Sampling Frequency

Fpass = 5000;            % Passband Frequency
Fstop = 6000;            % Stopband Frequency
Dpass = 0.057501127785;  % Passband Ripple
Dstop = 0.0001;          % Stopband Attenuation
dens  = 20;              % Density Factor

% Calculate the order from the parameters using FIRPMORD.
[N, Fo, Ao, W] = firpmord([Fpass, Fstop]/(Fs/2), [1 0], [Dpass, Dstop]);

% Calculate the coefficients using the FIRPM function.
b  = firpm(N, Fo, Ao, W, {dens});
Hd = dfilt.dffir(b);

% [EOF]