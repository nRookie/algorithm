# Algorithm learning notes

Use the repository-owned skills:

- [algorithm-practice](.agents/skills/algorithm-practice/SKILL.md) for algorithm
  learning summaries, implementation reviews, and study notes.
- [algorithm-step-by-step](.agents/skills/algorithm-step-by-step/SKILL.md) for
  interactive derivation and dry runs, one small question at a time.
- [algorithm-recap](.agents/skills/algorithm-recap/SKILL.md) for reorganizing old
  Markdown memos by dynamic topics and subtopics, converting C++ or Go code to
  Kotlin collections, and finding related LeetCode exercises.

Read the relevant local `SKILL.md` before applying it. Maintain these skills
in this repository so their instructions travel with the learning notes.

## Learning mode preferences

- Recap implementations should target the matched LeetCode problem for judging:
  use its required Kotlin API, indexing, types, and constraints while preserving
  the original algorithmic idea. Keep original AcWing code as a reference.
- For a new problem, default to step-by-step coaching: ask one small question
  at a time and wait for the learner's answer, unless they request another mode.
- For recap of a previously studied problem, default to a direct review and
  polished explanation. Review the supplied reasoning and code, correct gaps,
  and organize the notes without requiring the learner to repeat derivation
  or answer checkpoint questions.
- Use step-by-step derivation or interactive dry runs during recap only when
  the learner explicitly requests them. Clarifying genuinely missing problem
  details is still allowed; do not turn clarification into a guided quiz.

## Reusable concept notes

When the user asks “what can we learn from this?”, requests reusable takeaways,
or asks to remember an algorithm concept, update
`study-notes/algorithm-concepts-cheatsheet.md` as part of the task. Treat this
as a request to record the lessons, not merely to propose recording them.
Respect an explicit request for discussion only or no file changes.

- Read the existing cheatsheet first; refine matching entries instead of
  appending duplicates.
- Select only useful concepts supported by the current discussion. Do not
  expand into unrelated algorithms or reveal solutions to upcoming exercises.
- Keep each entry concise: the rule, conditions under which it holds, why it
  works, and a small example or pitfall when useful.
- Lead with an abstract, transferable concept. Use problems as examples or
  references; the entry must make sense without knowing the source problem.
- State important qualifications, such as BFS requiring equal edge costs for
  its shortest-path guarantee. Distinguish graph states from physical positions
  when history affects future moves.
- Link to the relevant problem's `EXPLANATION.md` if available. Keep full code,
  execution traces, and long proofs in the problem folder.
- Keep `study-notes/algorithm-solving-workflow.md` for the problem-solving
  process; use the cheatsheet for reusable facts and distinctions.
- In the final response, link the updated file and briefly identify what was
  added. A separate custom skill is not required for this repository workflow.
