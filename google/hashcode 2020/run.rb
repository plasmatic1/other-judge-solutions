require 'open3'

"""
Valid program arguments:

- skipcompile (alias: sc) - skips compilation
"""

input_set = 'e'
src_file = 'sol1.cpp'
args = '-Ofast -g'

def getfile(file)
    ret = ''
    File.open(file) { |f| ret = f.read() }
    ret
end

def writefile(file, data)
    File.open(file, 'w') { |f| f << data }
end

def now()
    Process.clock_gettime(Process::CLOCK_MONOTONIC)
end

input_file = nil
Dir.entries('.').each do |file|
    if file.start_with?("#{input_set}_")
        input_file = file
        puts "Found input file #{input_file}"
        break
    end
end
puts

if input_file.nil?
    puts "No input file found"
    exit -1
end

input = %x(type #{input_file})

if ARGV.include?('skipcompile') || ARGV.include?('sc')
    puts "Skipping compilation (switch specified)"
else
    puts "Compiling..."
    puts "Compiler output: #{%x(g++ #{args} sol1.cpp -o sol.exe)}"
end
puts

puts "Executing..."
start = now
output, error, status = Open3.capture3("./sol.exe", :stdin_data=>input)
elapsed = now - start
writefile("out_#{input_file}", output)
puts "Execution complete:"
puts

puts "Debug output: #{error}"
puts "Elapsed time: #{elapsed}s"
puts "Exit code: #{status}"
