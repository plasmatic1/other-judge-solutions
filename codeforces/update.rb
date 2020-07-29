# Props
main = 'Plasmatic'
alts = ['zey_zey_chen', 'chad_master_13221']

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
