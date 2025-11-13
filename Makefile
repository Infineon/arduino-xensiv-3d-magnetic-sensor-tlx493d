
FQBN   ?= infineon:psoc6:cy8ckit_062s2_ai
TARGET ?= test_interrupts_single

##############################################################################################################################################################
RESULT_DIRECTORY=_results
CLANGTIDY_OUTPUT=$(RESULT_DIRECTORY)/clang-tidy/check-clang-tidy
CPPCHECK_OUTPUT=$(RESULT_DIRECTORY)/cppcheck/check-cppcheck
##############################################################################################################################################################

TAG=latest

IFX_DOCKER_REGISTRY=dockerregistry-v2.vih.infineon.com/ifxmakers/makers-docker:$(TAG)

DOCKER_REGISTRY=ifxmakers/makers-docker:$(TAG)
GHCR_REGISTRY=ghcr.io/infineon/makers-docker:$(TAG)

REGISTRY=$(DOCKER_REGISTRY)

# Here PWD is ./extras/makers-devops 
# Therefore, we set myLocalWorkingDir to the root of the repository
DOCKER=docker run --rm -it -v $(PWD):/myLocalWorkingDir:rw $(REGISTRY)

CODECHECK=extras/makers-devops/src/python/code_checks/codeChecks.py
MERGEXML=extras/makers-devops/src/python/code_checks/merge_clang_tidy_cppcheck.py
PROJECTYAML=config/project.yml
USERYAML=config/user.yml
GENERATEREPORT=./extras/makers-devops/src/python/code_checks/run_generate_reports.sh

pull-container: 
	docker pull $(REGISTRY)
# 	find ./src/python/code_checks/ -name "*.sh" -exec chmod +x {} \;
	
run-container-check-all: pull-container
	$(DOCKER) python3 $(CODECHECK) --projectYAML $(PROJECTYAML) --userYAML $(USERYAML) --getAllCodeChecks
	$(DOCKER) python3 $(CODECHECK) --projectYAML $(PROJECTYAML) --userYAML $(USERYAML) --getAllHILChecks
	$(DOCKER) python3 $(CODECHECK) --projectYAML $(PROJECTYAML) --userYAML $(USERYAML) --runAllCodeChecks

run-container-source-cppcheck: pull-container
	$(DOCKER) python3 $(CODECHECK) --projectYAML $(PROJECTYAML) --userYAML $(USERYAML) --runCheck source-code-quality-cppcheck 

run-container-source-clang-tidy-check: pull-container
	$(DOCKER) python3 $(CODECHECK) --projectYAML $(PROJECTYAML) --userYAML $(USERYAML) --runCheck code-quality-clang-tidy 

run-container-test-cppcheck: pull-container
	$(DOCKER) python3 $(CODECHECK) --projectYAML $(PROJECTYAML) --userYAML $(USERYAML) --runCheck test-code-quality-cppcheck 

run-container-test-clang-tidy-check: pull-container
	$(DOCKER) python3 $(CODECHECK) --projectYAML $(PROJECTYAML) --userYAML $(USERYAML) --runCheck test-code-quality-clang-tidy 

run-container-clang-tidy-format: pull-container
	$(DOCKER) python3 $(CODECHECK) --projectYAML $(PROJECTYAML) --userYAML $(USERYAML) --runCheck code-quality-clang-format

run-container-black-format:
	$(DOCKER) python3 $(CODECHECK) --projectYAML $(PROJECTYAML) --userYAML $(USERYAML) --runCheck code-quality-black-format

run-container-generate-html-report: pull-container
	$(DOCKER) $(GENERATEREPORT) --results-dir $(RESULT_DIRECTORY)
#	firefox _results/cppcheck/check-cppcheck/html-report/index.html


##############################################################################################################################################################

test_project_schemata:
	$(DOCKER) python3 src/python/check_schemata/checkProjectYAMLSchema.py
	$(DOCKER) python3 src/python/check_schemata/checkUserYAMLSchema.py

##############################################################################################################################################################

##############################################################################################################################################################

# run stuff with container from docker hub
run-build-target: 
	(cd ../.. ; cd tests/arduino-core-tests ; make compile FQBN=$(FQBN) $(TARGET))

run-container-interactive: pull-container
	$(DOCKER)
