# Props
main = 'Plasmatic'
alts = ['thinking_space', 'wasureta', 'kenos']

# Update codeforces submissions
puts "Getting codeforces submissions..."
puts "Main account (#{main})"
%x(get-submissions -h #{main})

ctr = 1
alts.each { |acc|
	puts "\nAlt account ###{ctr} (#{acc})"
	%x(get-submissions -h #{acc})
	puts
	ctr += 1
}
