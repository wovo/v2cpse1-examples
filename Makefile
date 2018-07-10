.PHONY: clean All

All:
	@echo "----------Building project:[ 2016-2017-V2CPSE1-02-05-proxy - Debug ]----------"
	@cd "2016-2017-V2CPSE1-02-05-proxy" && "$(MAKE)" -f  "2016-2017-V2CPSE1-02-05-proxy.mk"
clean:
	@echo "----------Cleaning project:[ 2016-2017-V2CPSE1-02-05-proxy - Debug ]----------"
	@cd "2016-2017-V2CPSE1-02-05-proxy" && "$(MAKE)" -f  "2016-2017-V2CPSE1-02-05-proxy.mk" clean
