render-md-mermaid: scripts/render-md-mermaid.sh $(shell find . -name "*.md" -not -path "./node_modules/*")
	@for md in $(shell find . -name "*.md" -not -path "./node_modules/*"); do bash scripts/render-md-mermaid.sh "$$md"; done
