# Makes file for USACO training problem

prob_id = ARGV[0]
if prob_id.nil?
    puts "No ID specified!"
    exit -1
end
template = %x(type USACO_TRAINING_TEMPLATE) # Windows version of cat
out_file = template.gsub(/PROBLEM_ID/, prob_id)
File.open("usaco training/#{prob_id}.cpp", 'w') { |f| f << out_file }
puts "Made file for problem #{prob_id}!"
