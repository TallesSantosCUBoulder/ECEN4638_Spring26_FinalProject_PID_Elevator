close all; clear all ; clc;

% Define port
portName = '/dev/cu.usbmodem14301';
baudRate = 115200;    % Adjust if needed

% Open serial port
s = serialport(portName, baudRate);

% Flush any old data
flush(s);

% Initialize an empty string
concatenatedStr = '';

% Data matrix
n_tot_samples = 1e3;
n_columns = 3;
data_matrix = zeros(n_tot_samples, n_columns);
count_aux = 1;

% Continuous read loop
figure; 

while true
    if s.NumBytesAvailable > 0
        c = read(s, 1, 'char');  % Read one character

        concatenatedStr = [concatenatedStr, c];

        if c == newline
            fprintf('Received line: %s\n', concatenatedStr);

            numbers = regexp(concatenatedStr, '[-+]?[0-9]*\.?[0-9]+', 'match');
            numArray = str2double(numbers);

            if length(numArray) == n_columns
                data_matrix(count_aux, :) = numArray;
                count_aux = count_aux + 1;
            end

            concatenatedStr = '';

            
            if mod(count_aux, 100) == 0

                subplot(1,2,1)
                title('Position'); hold on ;
                plot(data_matrix(1:count_aux-1,1), '.-r');

                subplot(1,2,2)
                title('PWM'); hold on ;
                plot(data_matrix(1:count_aux-1,2), '.-r');
                ylim([0 255])
                
                drawnow;

            end
        end
    end
end

% Close port (this won't be reached in an infinite loop, consider adding an exit condition)
clear s;