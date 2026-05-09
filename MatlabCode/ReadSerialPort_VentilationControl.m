close all; clear all ; clc;

% define serial port used for device communication
portName = '/dev/cu.usbmodem14301';
baudRate = 115200;    % adjust if communication is unstable

% open serial connection
s = serialport(portName, baudRate);

% clear any existing buffered serial data
flush(s);

% initialize buffer for incoming serial line
concatenatedStr = '';

% preallocate storage for incoming data
n_tot_samples = 1e3;
n_columns = 3;
data_matrix = zeros(n_tot_samples, n_columns);
count_aux = 1;

% open figure for real time plotting
figure; 

% continuous acquisition loop
while true
    % check if serial data is available
    if s.NumBytesAvailable > 0
        
        % read one character from serial buffer
        c = read(s, 1, 'char');

        % append character to current line buffer
        concatenatedStr = [concatenatedStr, c];

        % detect end of line
        if c == newline
            
            % display received full line
            fprintf('Received line: %s\n', concatenatedStr);

            % extract numeric values from string
            numbers = regexp(concatenatedStr, '[-+]?[0-9]*\.?[0-9]+', 'match');
            numArray = str2double(numbers);

            % store values if correct format
            if length(numArray) == n_columns
                data_matrix(count_aux, :) = numArray;
                count_aux = count_aux + 1;
            end

            % reset buffer for next line
            concatenatedStr = '';

            % update plots every 100 samples
            if mod(count_aux, 100) == 0

                % plot position data
                subplot(1,2,1)
                title('Position'); hold on ;
                plot(data_matrix(1:count_aux-1,1), '.-r');

                % plot pwm signal
                subplot(1,2,2)
                title('PWM'); hold on ;
                plot(data_matrix(1:count_aux-1,2), '.-r');
                ylim([0 255])
                
                % refresh figure
                drawnow;

            end
        end
    end
end

% close serial port (not reached unless loop is interrupted)
clear s;